import TopPartGameBoard from "../components/FrameComponent";
import Answer from "../components/Answer";
import styles from "./GameBoard.module.css";
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constents from "../Constants";
import he from 'he';
import { useNavigate } from "react-router-dom";
import { useLocation } from 'react-router-dom';
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
  const timeOut = queryParams.get("answerTimeout");
  console.log('timeout:', timeOut)
  const colors = ["#ea9e8d", "#06bee1", "#006c67", "#ecc8af"];
  const icons = ["./iconparksolidonekey@2x.png", "/iconparksolidtwokey@2x.png", "/iconparksolidthreekey@2x.png", "/iconparksolidthreekey-1@2x.png"]
  const [shuffledArray, setShuffedledArray] = useState([]);

  const [question, setQestion] = useState("");
  const [answers, setAnswers] = useState([]);
  const [loading, setLoading] = useState(true);

  const [avgTime, setAvgTime] = useState(0);

  const [myAns, setMyAns] = useState(0);

  const [correctAnsCount, setcorrectAnsCount] = useState(0);
  const [wrongAnsCount, setWrongAnsCount] = useState(0);

  const [reset, setReset] = useState(false);
  const navigate = useNavigate();

  function getQuestions() {
    setLoading(true);
    socket.emit("getQuestion");
  }

  useEffect(() => {
    socket.on("getQuestionResponse", (response) => {
      if (response.status === Constents.WORK_STATUS) {
        setQestion(response[Constents.FIELDS.QUESTION]);
        setAnswers(shuffleArray(response[Constents.FIELDS.ANSWERS]));
        setLoading(false);
      }
    });

    socket.on("submitAnswerResponse", (response) => {
      if (response.status === Constents.WORK_STATUS) {
          if (response["correctAnswerId"] === myAns)
          {
            setcorrectAnsCount(prevCount => prevCount + 1);
          }
          else
          {
            setWrongAnsCount(prevCount => prevCount + 1);
          }
        setAvgTime(response["avg_time"])
        getQuestions();
      }
      else if (response.status === Constents.GAME_ENDED_FOR_USER)
      {
          navigate("/game-results")
      }
    });

    getQuestions();

    setShuffedledArray(shuffleArray(colors))
    return () => {
      socket.off("getQuestionResponse");
      socket.off("submitAnswerResponse");
    };
  }, [myAns]);

  const submitAnswer = (id) => {
    setMyAns(id);
    setReset(true);
    socket.emit("submitAnswer", { [Constents.FIELDS.ANSWER_ID]: id});
    getQuestions();
  };


  return (
    <div className={styles.gameBoard}>
      <TopPartGameBoard
        correctAns={correctAnsCount}
        allQuestions={wrongAnsCount}
        avgTime={avgTime.toFixed(3)}
        timeOut={timeOut}
        submitAns={submitAnswer}
        reset={reset}
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
