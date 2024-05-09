import styles from "./UserNameInput.module.css";

const UserNameInput = ({ placeHolder, icon }) => {
  return (
    <div className={styles.usernameInput}>
      <div className={styles.userNameParent}>
        <div className={styles.userName}>{placeHolder}</div>
        <div className={styles.inputWrapper}>
          <div className={styles.vectorParent}>
            <img className={styles.frameChild} alt="" src="/vector-2.svg" />
            <img className={styles.wpfnameIcon} alt="" src={icon} />
          </div>
        </div>
      </div>
    </div>
  );
};

export default UserNameInput;
