import PropTypes from "prop-types";
import styles from "./HeaderAddAQuestion.module.css";

const HeaderAddAQuestion = ({ className = "" }) => {
  return (
    <section className={[styles.frameWrapper, className].join(" ")}>
      <div className={styles.nestedContentParent}>
        <div className={styles.nestedContent}>
          <h3 className={styles.questionText}>Question text</h3>
        </div>
        <div className={styles.vectorWrapper}>
          <img
            className={styles.frameChild}
            loading="lazy"
            alt=""
            src="/vector-12.svg"
          />
        </div>
      </div>
    </section>
  );
};

HeaderAddAQuestion.propTypes = {
  className: PropTypes.string,
};

export default HeaderAddAQuestion;
