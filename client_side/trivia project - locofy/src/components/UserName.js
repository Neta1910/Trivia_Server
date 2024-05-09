import { useMemo } from "react";
import styles from "./UserName.module.css";

const UserName = ({ wpfnameIconWidth, wpfnameIconAlignSelf }) => {
  const userNameStyle = useMemo(() => {
    return {
      width: wpfnameIconWidth,
      alignSelf: wpfnameIconAlignSelf,
    };
  }, [wpfnameIconWidth, wpfnameIconAlignSelf]);

  return (
    <div className={styles.userName} style={userNameStyle}>
      <div className={styles.userNameParent}>
        <div className={styles.userName1}>User name</div>
        <div className={styles.addressForm}>
          <div className={styles.formElements}>
            <img
              className={styles.formElementsChild}
              alt=""
              src="/vector-2.svg"
            />
            <img className={styles.wpfnameIcon} alt="" src="/wpfname.svg" />
          </div>
        </div>
      </div>
    </div>
  );
};

export default UserName;
