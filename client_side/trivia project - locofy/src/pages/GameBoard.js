import FrameComponent from "../components/FrameComponent";
import Answer from "../components/Answer";
import styles from "./GameBoard.module.css";

function shuffleArray(array) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
  return array;
}


const GameBoard = () => {

  const colors = ["#ea9e8d", "#06bee1", "#006c67", "#ecc8af"]
  const shuffledColors = shuffleArray(colors);

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

                  <Answer 
                  answerText="Answer 1 text" 
                  icon="./iconparksolidonekey@2x.png" 
                  backgroundColor={shuffledColors[0]}
                  />

                  <Answer
                    answerText="Answer 2 text"
                    icon={"/iconparksolidtwokey@2x.png"}
                    backgroundColor={shuffledColors[1]}
                  />
              
              </div>
            </div>
          </div>

          <div className={styles.frameWrapper}>
            <div className={styles.frameParent1}>
                <Answer
                  answerText="Answer 3 text"
                  icon={"/iconparksolidthreekey@2x.png"}
                  backgroundColor={shuffledColors[2]}
                />

                <Answer
                  answerText="Answer 4 text"
                  icon={"/iconparksolidthreekey-1@2x.png"}
                  backgroundColor={shuffledColors[3]}
                />

            </div>
          </div>
        </section>
      </main>
    </div>
  );
};

export default GameBoard;
