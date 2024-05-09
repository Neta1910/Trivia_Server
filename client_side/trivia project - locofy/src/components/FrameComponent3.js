import UserStats from "./UserStats";
import styles from "./FrameComponent3.module.css";

const FrameComponent3 = () => {
  return (
    <section className={styles.userStatsParent}>
      <UserStats
        fluentgames24Filled="/fluentgames24filled.svg"
        youPlayedXGames="you played x games"
      />
      <div className={styles.userStatsGroup}>
        <UserStats
          fluentgames24Filled="/fluentgames24filled-1.svg"
          youPlayedXGames="Your highest score is x"
          propWidth="unset"
          propMinWidth="231px"
          propFlex="1"
          propBackground="linear-gradient(91.65deg, #ffee88, #06bee1)"
        />
        <div className={styles.userStats}>
          <div className={styles.yourAvgAnsContainer}>
            <p className={styles.yourAvgAns}>Your avg ans time</p>
            <p className={styles.yourAvgAns}>is x seconds</p>
          </div>
          <div className={styles.ellipseParent}>
            <div className={styles.frameChild} />
            <img
              className={styles.tableralarmAverageIcon}
              loading="lazy"
              alt=""
              src="/tableralarmaverage.svg"
            />
          </div>
        </div>
      </div>
    </section>
  );
};

export default FrameComponent3;
