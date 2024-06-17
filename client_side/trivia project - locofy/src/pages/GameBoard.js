import React, { useEffect, useState } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import TopPartGameBoard from "../components/FrameComponent";
import Answer from "../components/Answer";
import styles from "./GameBoard.module.css";
import { socket } from "../socket";
import Constents from "../Constants";
import he from 'he';

function shuffleArray(array) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
  return array;
}

const GameBoard = () => {
  const location = useLocation();
  const queryParams = new URLSearchParams(location.search);
  const timeOut = parseInt(queryParams.get("answerTimeout"), 10) || 0;
  console.log('timeout:', timeOut);

  const colors = ["#ea9e8d", "#06bee1", "#006c67", "#ecc8af"];
  const icons = [
    "./iconparksolidonekey@2x.png",
    "/iconparksolidtwokey@2x.png",
    "/iconparksolidthreekey@2x.png",
    "/iconparksolidthreekey-1@2x.png"
  ];
  const [shuffledArray, setShuffledArray] = useState(shuffleArray(colors));
  const [question, setQuestion] = useState("");
  const [answers, setAnswers] = useState([]);
  const [loading, setLoading] = useState(true);
  const [avgTime, setAvgTime] = useState(0);
  const [myAns, setMyAns] = useState(0);
  const [isGameEnd, setIsGameEnd] = useState(false);
  const [correctAnsCount, setCorrectAnsCount] = useState(0);
  const [wrongAnsCount, setWrongAnsCount] = useState(0);
  const [reset, setReset] = useState(false);
  const navigate = useNavigate();

  function getQuestions() {
    setLoading(true);
    socket.emit("getQuestion");
  }

  useEffect(() => {
    var timer = setTimeout(skipQuestion, timeOut * 1000);
    const handleGetQuestionResponse = (response) => {
      if (response.status === Constents.WORK_STATUS) {
        setQuestion(response[Constents.FIELDS.QUESTION]);
        setAnswers(shuffleArray(response[Constents.FIELDS.ANSWERS]));
        setLoading(false);
        if (timeOut && !isGameEnd) {
          timer = setTimeout(skipQuestion, timeOut * 1000);
          return () => clearTimeout(timer);
        }
      }
    };

    const handleSubmitAnswerResponse = (response) => {
      if (response.status === Constents.WORK_STATUS) {
        if (response["correctAnswerId"] === myAns) {
          setCorrectAnsCount((prevCount) => prevCount + 1);
        } else {
          setWrongAnsCount((prevCount) => prevCount + 1);
        }
        setAvgTime(response["avg_time"]);
        getQuestions();
      } else if (response.status === Constents.GAME_ENDED_FOR_USER) {
        setIsGameEnd(true);
        navigate("/game-results");
      }
    };

    socket.on("getQuestionResponse", handleGetQuestionResponse);
    socket.on("submitAnswerResponse", handleSubmitAnswerResponse);

    getQuestions();

    return () => {
      socket.off("getQuestionResponse", handleGetQuestionResponse);
      socket.off("submitAnswerResponse", handleSubmitAnswerResponse);
      clearTimeout(timer);
    };
  }, [myAns, timeOut, isGameEnd, navigate]);

  const submitAnswer = (id) => {
    setMyAns(id);
    setReset(true);
    socket.emit("submitAnswer", { [Constents.FIELDS.ANSWER_ID]: id });
  };

  function skipQuestion() {
    if (!isGameEnd) {
      submitAnswer(0);
    }
  }

  return (
    <div className={styles.gameBoard}>
      <TopPartGameBoard
        correctAns={correctAnsCount}
        allQuestions={wrongAnsCount}
        avgTime={avgTime.toFixed(3)}
        timeOut={timeOut}
      />

      <main className={styles.actuoelGame}>
        <section className={styles.frameParent}>
          <div className={styles.frameGroup}>
            <div className={styles.frameContainer}>
              <div className={styles.questionTextWrapper}>
                <div className={styles.questionText}>{he.decode(question)}</div>
              </div>
              <img
                className={styles.frameChild}
                loading="lazy"
                alt=""
                src="/vector-9.svg"
              />
            </div>

            <div className={styles.frameWrapper}>
              <div className={styles.frameDiv}>
                {answers.map((element, index) => (
                  <Answer
                    key={index}
                    answerText={answers[index][0]}
                    icon={icons[index]}
                    backgroundColor={shuffledArray[index]}
                    onClickFunc={() => submitAnswer(answers[index][0][0])}
                    id={index}
                  />
                ))}
              </div>
            </div>
          </div>
        </section>
      </main>
    </div>
  );
};

export default GameBoard;
