import FrameComponent2 from "../components/FrameComponent2";
import RoomCard1 from "../components/RoomCard1";
import RoomCard from "../components/RoomCard";
import styles from "./JoinRoom.module.css";

const JoinRoom = () => {
  return (
    <div className={styles.joinRoom}>
      <section className={styles.frameParent}>
        <FrameComponent2 />
        <RoomCard1 xPlayersDebugCommit="unset" />
      </section>
      <div className={styles.roomCardParent}>
        <div className={styles.roomCard}>
          <div className={styles.frameGroup}>
            <div className={styles.roomNameWrapper}>
              <div className={styles.roomName}>Room name</div>
            </div>
            <div className={styles.frameChild} />
            <div className={styles.xPlayersParent}>
              <div className={styles.xPlayers}>{`x players `}</div>
              <div className={styles.similarNamesForSubComponenParent}>
                <div className={styles.similarNamesForSubComponen}>
                  <img
                    className={styles.questionMarkerIcon}
                    loading="lazy"
                    alt=""
                    src="/vector-6.svg"
                  />
                </div>
                <div className={styles.similarNamesForSubComponen2}>
                  <div className={styles.xPlayers}>x timeout</div>
                  <div className={styles.similarNamesForSubComponenParent}>
                    <div className={styles.similarNamesForSubComponen}>
                      <img
                        className={styles.questionMarkerIcon}
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
        </div>
        <RoomCard />
      </div>
    </div>
  );
};

export default JoinRoom;
