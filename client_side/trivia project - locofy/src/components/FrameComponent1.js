import styles from "./FrameComponent1.module.css";

const FrameComponent1 = () => {
  return (
    <section className={styles.informationParent}>
      <div className={styles.information}>
        <div className={styles.vectorWrapper}>
          <img
            className={styles.vectorIcon}
            loading="lazy"
            alt=""
            src="/vector.svg"
          />
        </div>
        <h3 className={styles.thereIsXContainer}>
          <p className={styles.thereIsXQuestions}>
            <span className={styles.thereIsX}>{`There is x `}</span>
            <span className={styles.questions}>questions</span>
            <span>{` `}</span>
          </p>
          <p className={styles.thereIsXQuestions}>in this room</p>
        </h3>
      </div>
      <img
        className={styles.frameChild}
        loading="lazy"
        alt=""
        src="/vector-8.svg"
      />
      <div className={styles.informationWrapper}>
        <div className={styles.information1}>
          <div className={styles.mingcutetimefill}>
            <img
              className={styles.mingcutetimeFillIcon}
              loading="lazy"
              alt=""
              src="/mingcutetimefill.svg"
            />
          </div>
          <h3 className={styles.thereIsXContainer}>
            <p className={styles.thereIsXQuestions}>You have x seconds</p>
            <p className={styles.thereIsXQuestions}>
              <span>{`to answer each `}</span>
              <span className={styles.questions}>question</span>
            </p>
          </h3>
        </div>
      </div>
    </section>
  );
};

export default FrameComponent1;
