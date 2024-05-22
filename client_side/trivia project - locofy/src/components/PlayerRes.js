import { useMemo } from "react";
import styles from "./PlayerRes.module.css";

const PlayerRes = ({ Playername, correctAns, avgTime, place }) => {

  const icons = ["/firstPlaceGameRes(1).png", "/firstPlaceGameRes(3).png", "/firstPlaceGameRes(2).png"]

  return (
    <div className={styles.playerRes}>
      <div className={styles.userStats}>
        <div className={styles.userName}>{Playername}</div>
        <div className={styles.scoreMetrics}>
          <div className={styles.accuracyTime}>
            <img
              className={styles.accuracyIcon}
              loading="lazy"
              alt=""
              src={"vector-11.svg"}
            />
            <div className={styles.xCorrectAns}>{correctAns} correct ans</div>
          </div>
        </div>
        <div className={styles.avgTime}>
          <div className={styles.avgTimeX}>Avg time: {avgTime} seconds</div>
        </div>
      </div>
      {place <= 2 ? 
      <img
        className={styles.iconParkSolidoneKey}
        loading="lazy"
        alt=""
        src={icons[2]}
      />
        : null }
    </div>
  );
};

export default PlayerRes;
