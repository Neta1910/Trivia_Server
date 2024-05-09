import styles from "./CreateRoom.module.css";

const CreateRoom = () => {
  return (
    <div className={styles.createRoom}>
      <div className={styles.createRoomInner}>
        <div className={styles.rectangleParent}>
          <div className={styles.frameChild} />
          <h2 className={styles.createRoom1}>Create room</h2>
          <div className={styles.fRAMEWrapper}>
            <div className={styles.fRAME}>
              <button className={styles.roomNameParent}>
                <div className={styles.roomName}>Room name</div>
                <div className={styles.frameWrapper}>
                  <div className={styles.vectorParent}>
                    <img
                      className={styles.frameItem}
                      alt=""
                      src="/vector-2.svg"
                    />
                    <img
                      className={styles.wpfnameIcon}
                      alt=""
                      src="/wpfname.svg"
                    />
                  </div>
                </div>
              </button>
              <div className={styles.questionTimeOutQuestionParent}>
                <button className={styles.questionTimeOutQuestion}>
                  <div className={styles.questionTimeout}>Question timeOut</div>
                  <div className={styles.questionTimeOutQuestionInner}>
                    <div className={styles.mingcutetimeFillParent}>
                      <img
                        className={styles.mingcutetimeFillIcon}
                        alt=""
                        src="/mingcutetimefill.svg"
                      />
                      <img
                        className={styles.frameItem}
                        alt=""
                        src="/vector-2.svg"
                      />
                    </div>
                  </div>
                </button>
                <button className={styles.questionTimeOutQuestion1}>
                  <div className={styles.questionTimeout}>
                    Amount of players
                  </div>
                  <div className={styles.frameParent}>
                    <div className={styles.vectorWrapper}>
                      <img
                        className={styles.vectorIcon}
                        alt=""
                        src="/vector-2.svg"
                      />
                    </div>
                    <img
                      className={styles.gameIconstabletopPlayers}
                      alt=""
                      src="/gameiconstabletopplayers.svg"
                    />
                  </div>
                </button>
              </div>
              <div className={styles.menuBarWrapper}>
                <button className={styles.menuBar}>
                  <div className={styles.questionCount}>Question count</div>
                  <div className={styles.menuBarInner}>
                    <div className={styles.vectorGroup}>
                      <img
                        className={styles.frameItem}
                        alt=""
                        src="/vector-2.svg"
                      />
                      <img
                        className={styles.pajamasquestionIcon}
                        alt=""
                        src="/pajamasquestion.svg"
                      />
                    </div>
                  </div>
                </button>
              </div>
              <div className={styles.fRAMEInner}>
                <button className={styles.submitWrapper}>
                  <div className={styles.submit}>Submit</div>
                </button>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div className={styles.createRoomChild}>
        <img
          className={styles.frameChild2}
          loading="lazy"
          alt=""
          src="/vector-5.svg"
        />
      </div>
      <img
        className={styles.menuBarIcon}
        loading="lazy"
        alt=""
        src="/menu-bar.svg"
      />
    </div>
  );
};

export default CreateRoom;
