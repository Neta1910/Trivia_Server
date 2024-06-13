import PropTypes from "prop-types";
import styles from "./HeaderAddAQuestion.module.css";

const HeaderAddAQuestion = ({ className = "", onChange }) => {
  const handeleChang = (e) => {
    onChange(e.target.value);
  }
  return (
    <section className={[styles.frameWrapper, className].join(" ")}>
      <div className={styles.nestedContentParent}>
        <div className={styles.nestedContent}>
          <textarea className={styles.questionText} placeholder="Question text"  onChange={(e) => handeleChang(e)} />
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
