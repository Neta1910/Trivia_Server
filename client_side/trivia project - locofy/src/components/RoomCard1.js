import { useMemo } from "react";
import styles from "./RoomCard1.module.css";

const RoomCard1 = ({ xPlayersDebugCommit }) => {
  const roomCardStyle = useMemo(() => {
    return {
      debugCommit: xPlayersDebugCommit,
    };
  }, [xPlayersDebugCommit]);

  return (
    <div className={styles.roomCard} style={roomCardStyle}>
      <div className={styles.frameParent}>
        <div className={styles.roomNameWrapper}>
          <div className={styles.roomName}>Room name</div>
        </div>
        <div className={styles.frameChild} />
        <div className={styles.xPlayersParent}>
          <div className={styles.xPlayers}>{`x players `}</div>
          <div className={styles.frameGroup}>
            <div className={styles.horizontalAxisWrapper}>
              <img
                className={styles.horizontalAxisIcon}
                loading="lazy"
                alt=""
                src="/vector-6.svg"
              />
            </div>
            <div className={styles.xTimeoutWrapper}>
              <div className={styles.xTimeout}>x timeout</div>
            </div>
            <div className={styles.instanceOfCard}>
              <div className={styles.horizontalAxisWrapper}>
                <img
                  className={styles.horizontalAxisIcon}
                  loading="lazy"
                  alt=""
                  src="/vector-6.svg"
                />
              </div>
              <div className={styles.xPlayers}>x questions</div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default RoomCard1;
