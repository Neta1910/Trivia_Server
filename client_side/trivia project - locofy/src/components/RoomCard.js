import styles from "./RoomCard.module.css";

const RoomCard = () => {
  return (
    <div className={styles.roomCard}>
      <div className={styles.frameParent}>
        <div className={styles.roomNameWrapper}>
          <div className={styles.roomName}>Room name</div>
        </div>
        <div className={styles.frameChild} />
        <div className={styles.frameGroup}>
          <div className={styles.xPlayersWrapper}>
            <div className={styles.xPlayers}>{`x players `}</div>
          </div>
          <div className={styles.vectorWrapper}>
            <img
              className={styles.frameItem}
              loading="lazy"
              alt=""
              src="/vector-6.svg"
            />
          </div>
          <div className={styles.xQuestions}>
            <div className={styles.xTimeout}>x timeout</div>
            <div className={styles.questionsList}>
              <div className={styles.vectorWrapper}>
                <img
                  className={styles.frameItem}
                  loading="lazy"
                  alt=""
                  src="/vector-6.svg"
                />
              </div>
              <div className={styles.xQuestions1}>x questions</div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default RoomCard;
