import { useMemo } from "react";
import Answer from "./Answer";
import styles from "./AnswerComp.module.css";

const AnswerComp = ({
  answerText,
  icon,
  propBackgroundColor,
  propTop,
  showIconParkSolidoneKey,
}) => {
  const answer1Style = useMemo(() => {
    return {
      backgroundColor: propBackgroundColor,
    };
  }, [propBackgroundColor]);

  const iconParkSolidtwoKeyStyle = useMemo(() => {
    return {
      top: propTop,
    };
  }, [propTop]);

  return (
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
        src={icon}
        style={iconParkSolidtwoKeyStyle}
      />
    </div>
  );
};

export default AnswerComp;
