import Ans from "../components/Ans";
import styles from "./AddQuestion.module.css";
import HeaderAddAQuestion from "../components/HeaderAddAQuestion";
import { useState } from "react";

const AddAQuestion = () => {
  const [questionText, setQuestionText] = useState("");
  const [otherAnswers, setOtherAnswers] = useState([]);

  const handleAnswerChange = (index, event) => {
    const newAnswers = [...otherAnswers];
    newAnswers[index] = event.target.value;
    setOtherAnswers(newAnswers);
  };

  const handleFormSubmit = () => {
    
  };

  return (
    <div className={styles.addAQuestion}>
      <h3 className={styles.addAQuestion1}>Add a question</h3>
      <main className={styles.frameParent}>
        <HeaderAddAQuestion />
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
