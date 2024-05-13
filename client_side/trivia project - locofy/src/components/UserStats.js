import { useMemo } from "react";
import styles from "./UserStats.module.css";

const UserStats = ({
    icon,
    nameStat,
    background,
  }) => {

  const ellipseDivStyle = useMemo(() => {
    return {
      background: background,
    };
  }, [background]);

  return (
    <div className={styles.userStats}>
      <div className={styles.ellipseParent}>
        <div className={styles.frameChild} style={ellipseDivStyle} />
        <img
          className={styles.fluentgames24FilledIcon}
          loading="lazy"
          alt=""
          src={icon}
        />
      </div>
      <div className={styles.youPlayedX}>{nameStat}</div>
    </div>
  );
};

export default UserStats;
