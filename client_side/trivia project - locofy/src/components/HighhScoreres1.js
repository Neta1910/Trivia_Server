import styles from "./HighhScoreres1.module.css";

const HighhScoreres1 = () => {
  return (
    <div className={styles.highhScoreres}>
      <div className={styles.player}>
        <div className={styles.playerNames}>
          <div className={styles.playerNamesChild} />
          <div className={styles.semicolonPlacement}>1</div>
        </div>
        <div className={styles.userName}>User name</div>
        <div className={styles.score}>Score</div>
      </div>
      <div className={styles.player1}>
        <div className={styles.playerNames}>
          <div className={styles.playerNamesChild} />
          <div className={styles.div}>2</div>
        </div>
        <div className={styles.userName}>User name</div>
        <div className={styles.score}>Score</div>
      </div>
      <div className={styles.player2}>
        <div className={styles.playerNames}>
          <div className={styles.playerNamesChild} />
          <div className={styles.div1}>3</div>
        </div>
        <div className={styles.userName}>User name</div>
        <div className={styles.score}>Score</div>
      </div>
    </div>
  );
};

export default HighhScoreres1;
