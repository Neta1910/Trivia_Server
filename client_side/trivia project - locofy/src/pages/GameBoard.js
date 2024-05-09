import FrameComponent from "../components/FrameComponent";
import Answer from "../components/Answer";
import styles from "./GameBoard.module.css";

const GameBoard = () => {
  return (
    <div className={styles.gameBoard}>
      <FrameComponent />
      <main className={styles.actuoelGame}>
        <section className={styles.frameParent}>
          <div className={styles.frameGroup}>
            <div className={styles.frameContainer}>
              <div className={styles.questionTextWrapper}>
                <div className={styles.questionText}>Question text</div>
              </div>
              <img
                className={styles.frameChild}
                loading="lazy"
                alt=""
                src="/vector-9.svg"
              />
            </div>
            <div className={styles.frameWrapper}>
              <div className={styles.frameDiv}>
                <div className={styles.answer1Wrapper}>
                  <Answer answer1Text="Answer 1 text" showIconParkSolidoneKey />
                </div>
                <div className={styles.answer2Parent}>
                  <Answer
                    answer1Text="Answer 2 text"
                    showIconParkSolidoneKey={false}
                    propAlignSelf="unset"
                    propBackgroundColor="#06bee1"
                    propPadding="var(--padding-7xl) var(--padding-sm)"
                    propGap="unset"
                    propPosition="absolute"
                    propTop="0px"
                    propLeft="0px"
                    propWidth="100%"
                    propHeight="100%"
                  />
                  <img
                    className={styles.iconParkSolidtwoKey}
                    loading="lazy"
                    alt=""
                    src="/iconparksolidtwokey@2x.png"
                  />
                </div>
              </div>
            </div>
          </div>
          <div className={styles.frameWrapper}>
            <div className={styles.frameParent1}>
              <div className={styles.answer2Parent}>
                <Answer
                  answer1Text="Answer 3 text"
                  showIconParkSolidoneKey={false}
                  propAlignSelf="unset"
                  propBackgroundColor="#ea9e8d"
                  propPadding="var(--padding-7xl) var(--padding-sm)"
                  propGap="unset"
                  propPosition="absolute"
                  propTop="0px"
                  propLeft="0px"
                  propWidth="100%"
                  propHeight="100%"
                />
                <img
                  className={styles.iconParkSolidthreeKey}
                  loading="lazy"
                  alt=""
                  src="/iconparksolidthreekey@2x.png"
                />
              </div>
              <div className={styles.answer2Parent}>
                <Answer
                  answer1Text="Answer 4 text"
                  showIconParkSolidoneKey={false}
                  propAlignSelf="unset"
                  propBackgroundColor="#006c67"
                  propPadding="var(--padding-7xl) var(--padding-sm)"
                  propGap="unset"
                  propPosition="absolute"
                  propTop="0px"
                  propLeft="0px"
                  propWidth="100%"
                  propHeight="100%"
                />
                <img
                  className={styles.iconParkSolidthreeKey}
                  alt=""
                  src="/iconparksolidthreekey-1@2x.png"
                />
              </div>
            </div>
          </div>
        </section>
      </main>
    </div>
  );
};

export default GameBoard;
