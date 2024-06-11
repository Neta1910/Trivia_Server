import Ans from "../components/Ans";
import styles from "./AddQuestion.module.css";
import HeaderAddAQuestion from "../components/HeaderAddAQuestion";

const AddAQuestion = () => {
  return (
    <div className={styles.addAQuestion}>
      <h3 className={styles.addAQuestion1}>Add a question</h3>
      <main className={styles.frameParent}>
        <HeaderAddAQuestion />
        <section className={styles.ansParent}>
          <Ans correctAns="Correct ans" />
          <Ans correctAns="Answer 2" propBackgroundColor="#06bee1" />
        </section>
        <section className={styles.ansGroup}>
          <Ans correctAns="Answer 3" propBackgroundColor="#9c5151" />
          <Ans correctAns="Answer 4" propBackgroundColor="#006c67" />
        </section>
      </main>
    </div>
  );
};

export default AddAQuestion;
