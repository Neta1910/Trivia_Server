import TopPartGameBoard from "../components/FrameComponent";
import Answer from "../components/Answer";
import styles from "./GameBoard.module.css";
import { useEffect, useMemo, useState } from "react";
import { socket } from "../socket";
import Constents from "../Constants";
import he from 'he';
import { useNavigate } from "react-router-dom";

function shuffleArray(array) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
  return array;
}

const GameBoard = () => {
  const colors = ["#ea9e8d", "#06bee1", "#006c67", "#ecc8af"];
  const icons = ["./iconparksolidonekey@2x.png", "/iconparksolidtwokey@2x.png", "/iconparksolidthreekey@2x.png", "/iconparksolidthreekey-1@2x.png"]
  const [shuffledArray, setShuffedledArray] = useState([]);

  const [question, setQestion] = useState("");
  const [answers, setAnswers] = useState([]);
  const [loading, setLoading] = useState(true);
  const [answerTimes, setAnswerTime] = useState([]);

  const [startTime, setStartTime] = useState(null);
  const [endTime, setEndTime] = useState(null);

  const [correctAns, setCorrectAns] = useState(0);
  const [myAns, setMyAns] = useState(0);

  const [correctAnsCount, setcorrectAnsCount] = useState(0);
  const [wrongAnsCount, setWrongAnsCount] = useState(0);

  const navigate = useNavigate();

  const avgTime = useMemo(() => {
    const sum = answerTimes.reduce((accumulator, currentValue) => {
      return accumulator + currentValue;
    }, 0);
    return sum / answerTimes.length;
  }, [answerTimes]);

  function getQuestions() {
    setLoading(true);
    socket.emit("getQuestion");
  }

  useEffect(() => {
    socket.on("getQuestionResponse", (response) => {
      console.log(response);
      if (response.status === Constents.WORK_STATUS) {
        setQestion(response[Constents.FIELDS.QUESTION]);
        setAnswers(response[Constents.FIELDS.ANSWERS]);
        setLoading(false);
        startTimeFunc();
      }
    });

    socket.on("submitAnswerResponse", (response) => {
      if (response.status === Constents.WORK_STATUS) {
        response[Constents.FIELDS.ANSWER_ID] === myAns
          ? setcorrectAnsCount(correctAnsCount + 1)
          : setWrongAnsCount(wrongAnsCount + 1);
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
  }, []);

  const startTimeFunc = () => {
    const now = new Date().getTime();
    setStartTime(now);
    setEndTime(null); // Reset end time if the action is restarted
  };

  const endTimeFunc = () => {
    const now = new Date().getTime();
    setEndTime(now);
  };

  const submitAnswer = (id) => {
    setMyAns(id);
    endTimeFunc();
    const duration = (endTime - startTime) / 1000; // Convert milliseconds to seconds
    answerTimes.push(duration);
    socket.emit("submitAnswer", { [Constents.FIELDS.ANSWER_ID]: id });
    getQuestions();
  };

  // if (loading) return <p>Loaidng answers</p>

  return (
    <div className={styles.gameBoard}>
      <TopPartGameBoard
        correctAns={correctAnsCount}
        allQuestions={wrongAnsCount}
        avgTime={avgTime}
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
                    onClickFunc={() => submitAnswer(index)}
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
