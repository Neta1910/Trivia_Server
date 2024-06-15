import { useMemo } from "react";
import PropTypes from "prop-types";
import styles from "./Ans.module.css";

const Ans = ({ className = "", correctAns, propBackgroundColor, onChange, index = 0 }) => {
  const ansStyle = useMemo(() => {
    return {
      backgroundColor: propBackgroundColor,
    };
  }, [propBackgroundColor]);

  return (
    <div className={[styles.ans, className].join(" ")} style={ansStyle}>
      <textarea className={styles.correctAns} placeholder={correctAns}   onChange={(e) => onChange(index, e)}  />
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
