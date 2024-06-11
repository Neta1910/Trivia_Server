import { useMemo } from "react";
import PropTypes from "prop-types";
import styles from "./Ans.module.css";

const Ans = ({ className = "", correctAns, propBackgroundColor }) => {
  const ansStyle = useMemo(() => {
    return {
      backgroundColor: propBackgroundColor,
    };
  }, [propBackgroundColor]);

  return (
    <div className={[styles.ans, className].join(" ")} style={ansStyle}>
      <div className={styles.correctAns}>{correctAns}</div>
    </div>
  );
};

Ans.propTypes = {
  className: PropTypes.string,
  correctAns: PropTypes.string,

  /** Style props */
  propBackgroundColor: PropTypes.any,
};

export default Ans;
