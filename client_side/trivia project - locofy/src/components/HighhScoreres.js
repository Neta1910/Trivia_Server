import styles from "./HighhScoreres.module.css";

const HighhScoreres = () => {
  return (
    <div className={styles.highhScoreres}>
      <div className={styles.player}>
        <div className={styles.frameParent}>
          <div className={styles.circleShapeParent}>
            <div className={styles.circleShape} />
            <div className={styles.separator}>1</div>
          </div>
          <div className={styles.userName}>User name</div>
        </div>
        <div className={styles.scoreWrapper}>
          <div className={styles.score}>Score</div>
        </div>
      </div>
      <div className={styles.player}>
        <div className={styles.frameGroup}>
          <div className={styles.circleShapeParent}>
            <div className={styles.circleShape} />
            <div className={styles.div}>2</div>
          </div>
          <div className={styles.userName}>User name</div>
        </div>
        <div className={styles.scoreWrapper}>
          <div className={styles.score}>Score</div>
        </div>
      </div>
      <div className={styles.player}>
        <div className={styles.frameContainer}>
          <div className={styles.circleShapeParent}>
            <div className={styles.circleShape} />
            <div className={styles.div1}>3</div>
          </div>
          <div className={styles.userName}>User name</div>
        </div>
        <div className={styles.scoreWrapper}>
          <div className={styles.score}>Score</div>
        </div>
      </div>
    </div>
  );
};

export default HighhScoreres;
