import { useMemo } from "react";
import styles from "./Password.module.css";

const Password = ({ propWidth, propAlignSelf }) => {
  const passwordStyle = useMemo(() => {
    return {
      width: propWidth,
      alignSelf: propAlignSelf,
    };
  }, [propWidth, propAlignSelf]);

  return (
    <div className={styles.password} style={passwordStyle}>
      <div className={styles.mdipasswordParent}>
        <div className={styles.mdipassword} />
        <div className={styles.passwordWrapper}>
          <div className={styles.password1}>Password</div>
        </div>
        <div className={styles.vectorParent}>
          <img className={styles.vectorIcon} alt="" src="/vector.svg" />
          <img className={styles.inputIcons} alt="" src="/vector-2.svg" />
        </div>
      </div>
    </div>
  );
};

export default Password;
