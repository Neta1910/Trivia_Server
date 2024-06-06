import styles from "./FrameComponent.module.css";

const TopPartGameBoard = ({correctAns, allQuestions, avgTime}) => {
  return (
    <header className={styles.gameBoardInner}>
      <div className={styles.frameParent}>
        <div className={styles.xYCorrectAllQuestionsWrapper}>
          <div className={styles.xYContainer}>
            <p className={styles.x}>{correctAns} / {allQuestions}</p>
            <p className={styles.correctAll}> Correct / Wrong</p>
          </div>
        </div>
        <div className={styles.vectorWrapper}>
          <img
            className={styles.frameChild}
            loading="lazy"
            alt=""
            src="/vector-10.svg"
          />
        </div>
        <div className={styles.xSecondsAvgTimeWrapper}>
          <div className={styles.xSecondsAvg}>{avgTime} seconds, avg time</div>
        </div>
      </div>
    </header>
  );
};

export default TopPartGameBoard ;
