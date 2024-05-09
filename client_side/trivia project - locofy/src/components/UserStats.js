import { useMemo } from "react";
import styles from "./UserStats.module.css";

const UserStats = ({
  fluentgames24Filled,
  youPlayedXGames,
  propWidth,
  propMinWidth,
  propFlex,
  propBackground,
}) => {
  const userStatsStyle = useMemo(() => {
    return {
      width: propWidth,
      minWidth: propMinWidth,
      flex: propFlex,
    };
  }, [propWidth, propMinWidth, propFlex]);

  const ellipseDivStyle = useMemo(() => {
    return {
      background: propBackground,
    };
  }, [propBackground]);

  return (
    <div className={styles.userStats} style={userStatsStyle}>
      <div className={styles.ellipseParent}>
        <div className={styles.frameChild} style={ellipseDivStyle} />
        <img
          className={styles.fluentgames24FilledIcon}
          loading="lazy"
          alt=""
          src={fluentgames24Filled}
        />
      </div>
      <div className={styles.youPlayedX}>{youPlayedXGames}</div>
    </div>
  );
};

export default UserStats;
