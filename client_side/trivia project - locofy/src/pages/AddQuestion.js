import Ans from "../components/Ans";
import styles from "./AddQuestion.module.css";
import HeaderAddAQuestion from "../components/HeaderAddAQuestion";
import { useEffect, useState } from "react";
import { socket } from "../socket";
import Constants from "../Constants";
import { useNavigate } from "react-router-dom";

const AddAQuestion = () => {
  const [questionText, setQuestionText] = useState("");
  const [otherAnswers, setOtherAnswers] = useState([]);
  const navigate = useNavigate();

  const handleAnswerChange = (index, event) => {
    const newAnswers = [...otherAnswers];
    newAnswers[index] = event.target.value;
    setOtherAnswers(newAnswers);
  };


  const handleFormSubmit = () => {
    socket.emit("addQuestion", {[Constants.FIELDS.QUESTION_TEXT]: questionText, [Constants.FIELDS.ANSWERS]: otherAnswers})
  };

  useEffect (() => {
    socket.on("addQuestionResponse", (response) => {
      if (response.status === Constants.WORK_STATUS) {
        navigate('/menu')
      }
      else {
        console.log("Failed");
      }
    })
  })

  return (
    <div className={styles.addAQuestion}>
      <h3 className={styles.addAQuestion1}>Add a question</h3>
      <main className={styles.frameParent}>
        <HeaderAddAQuestion onChange={setQuestionText}/>
        <section className={styles.ansParent}>
          <Ans
            correctAns="Correct ans"
            onChange={handleAnswerChange}
            index={0}
          />
          <Ans
            correctAns="Answer 2"
            propBackgroundColor="#06bee1"
            onChange={handleAnswerChange}
            index={1}
          />
        </section>
        <section className={styles.ansGroup}>
          <Ans
            correctAns="Answer 3"
            propBackgroundColor="#9c5151"
            onChange={handleAnswerChange}
            index={2}
          />
          <Ans
            correctAns="Answer 4"
            propBackgroundColor="#006c67"
            onChange={handleAnswerChange}
            index={3}
          />
        </section>

        <section className={styles.submitButtonWrapper}>
          <button className={styles.submitButton}>
            <div className={styles.submit} onClick={handleFormSubmit}>
              Submit Question
            </div>
          </button>
        </section>
      </main>
    </div>
  );
};

export default AddAQuestion;
