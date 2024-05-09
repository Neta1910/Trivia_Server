import { useMemo } from "react";
import styles from "./Answer.module.css";

const Answer = ({
  answer1Text,
  showIconParkSolidoneKey,
  propAlignSelf,
  propBackgroundColor,
  propPadding,
  propGap,
  propPosition,
  propTop,
  propLeft,
  propWidth,
  propHeight,
}) => {
  const answer1Style = useMemo(() => {
    return {
      alignSelf: propAlignSelf,
      backgroundColor: propBackgroundColor,
      padding: propPadding,
      gap: propGap,
      position: propPosition,
      top: propTop,
      left: propLeft,
      width: propWidth,
      height: propHeight,
    };
  }, [
    propAlignSelf,
    propBackgroundColor,
    propPadding,
    propGap,
    propPosition,
    propTop,
    propLeft,
    propWidth,
    propHeight,
  ]);

  return (
    <div className={styles.answer1} style={answer1Style}>
      {showIconParkSolidoneKey && (
        <img
          className={styles.iconParkSolidoneKey}
          loading="lazy"
          alt=""
          src="/iconparksolidonekey@2x.png"
        />
      )}
      <div className={styles.answer1Text}>{answer1Text}</div>
    </div>
  );
};

export default Answer;
