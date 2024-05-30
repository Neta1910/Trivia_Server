import { useMemo } from "react";
import styles from "./Answer.module.css";

const Answer = ({
  answerText,
  icon,
  backgroundColor,
  onClickFunc,
}) => {

  const style = {
    backgroundColor: backgroundColor
  };

  return (
  <div className={styles.answer1Wrapper} onClick={onClickFunc}>
    <div className={styles.answer1}  style={style}>
        <img
          className={styles.iconParkSolidoneKey}
          loading="lazy"
          alt=""
          src={icon}
        />
      <div className={styles.answer1Text}>{answerText[1]}</div>
    </div>
  </div>
  );
};

export default Answer;
