import FrameComponent from "../components/FrameComponent";
import Answer from "../components/Answer";
import AnswerComp from "../components/AnswerComp";
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
                <AnswerComp
                  answerText="Answer 2 text"
                  icon="/iconparksolidtwokey@2x.png"
                  showIconParkSolidoneKey={false}
                />
              </div>
            </div>
          </div>
          <div className={styles.frameWrapper}>
            <div className={styles.frameDiv}>
              <AnswerComp
                answerText="Answer 3 text"
                icon="/iconparksolidthreekey@2x.png"
                propBackgroundColor="#ea9e8d"
                propTop="26px"
                showIconParkSolidoneKey={false}
              />
              <AnswerComp
                answerText="Answer 4 text"
                icon="/iconparksolidthreekey-1@2x.png"
                propBackgroundColor="#006c67"
                propTop="26px"
                showIconParkSolidoneKey={false}
              />
            </div>
          </div>
        </section>
      </main>
    </div>
  );
};

export default GameBoard;
