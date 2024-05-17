import TopPartGameBoard from "../components/FrameComponent";
import Answer from "../components/Answer";
import styles from "./GameBoard.module.css";
import { useEffect, useMemo, useState } from "react";
import {socket} from '../socket'
import Constents from '../Constants'
import { useSearchParams } from "react-router-dom";

function shuffleArray(array) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
  return array;
}


const GameBoard = () => {

  const colors = ["#ea9e8d", "#06bee1", "#006c67", "#ecc8af"]
  const shuffledColors = shuffleArray(colors);

  const [question, setQestion] = useState('')
  const [answers, setAnswers] = useState([])
  const [loading, setLoading] = useState(true);
  const [answerTimes, setAnswerTime] = useState([])

  const [startTime, setStartTime] = useState(null);
  const [endTime, setEndTime] = useState(null);

  const [correctAns, setCorrectAns] = useState(0)
  const [myAns, setMyAns] = useState(0);

  const [correctAnsCount, setcorrectAnsCount] = useState(0);
  const [wrongAnsCount, setWrongAnsCount] = useState(0);

  const avgTime = useMemo(() => {
    const sum = answerTimes.reduce((accumulator, currentValue) => {
      return accumulator + currentValue;
    }, 0);
    return sum / answerTimes.length
  }, [answerTimes])

  function getQuestions () {
    setLoading(true);
    socket.emit("getQuestion")
  }

  useEffect(() => {
    socket.on("getQuestionResponse", (response) => {
        if (response.status === Constents.WORK_STATUS) {
          setQestion(response[Constents.FIELDS.QUESTION])
          setAnswers(response[Constents.FIELDS.ANSWERS])
          setLoading(false);
          startTimeFunc();
        }

    })

    socket.on("submitAnswerResponse", (response) => {
      if (response.status == Constents.WORK_STATUS) {
        setCorrectAns(response[Constents.FIELDS.ANSWER_ID])
        correctAns === myAns ? setcorrectAnsCount(correctAnsCount + 1) : setWrongAnsCount(wrongAnsCount + 1)
      }
    })

    getQuestions();

    return (
      () => {
        socket.off("getQuestionResponse")
        socket.off("submitAnswerResponse")
      }
    )
  }, [])

  const startTimeFunc = () => {
    const now = new Date().getTime();
    setStartTime(now);
    setEndTime(null); // Reset end time if the action is restarted
    setDuration(null); // Reset duration if the action is restarted
  };

  const endTimeFunc = () => {
    const now = new Date().getTime();
    setEndTime(now);
  };


  const submitAnswer = (id) => {
    setMyAns(id)
    endTimeFunc();
    const duration = (endTime - startTime) / 1000; // Convert milliseconds to seconds
    answerTimes.push(duration);
    socket.emit("submitAnswer", {[Constents.FIELDS.ANSWER_ID]: id})
    getQuestions();
  }
  
  if (loading) return <p>Loaidng answers</p>

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
                <div className={styles.questionText}>{question}</div>
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

                  <Answer 
                  answerText= {answers[0]}
                  icon="./iconparksolidonekey@2x.png" 
                  backgroundColor={shuffledColors[0]}
                  onClickFunc={submitAnswer}
                  id = {1}
                  />

                  <Answer
                    answerText={answers[1]}
                    icon={"/iconparksolidtwokey@2x.png"}
                    backgroundColor={shuffledColors[1]}
                    onClickFunc={submitAnswer}
                    id={2}
                  />
              
              </div>
            </div>
          </div>

          <div className={styles.frameWrapper}>
            <div className={styles.frameParent1}>
                <Answer
                  answerText={answers[2]}
                  icon={"/iconparksolidthreekey@2x.png"}
                  backgroundColor={shuffledColors[2]}
                  onClickFunc={submitAnswer}
                  id={3}
                />

                <Answer
                  answerText={answers[3]}
                  icon={"/iconparksolidthreekey-1@2x.png"}
                  backgroundColor={shuffledColors[3]}
                  onClickFunc={submitAnswer}
                  id={4}
                />

            </div>
          </div>
        </section>
      </main>
    </div>
  );
};

export default GameBoard;
