import UserName from "./UserName";
import Password from "./Password";
import styles from "./TextInput.module.css";

const TextInput = () => {
  return (
    <div className={styles.textInput}>
      <div className={styles.register}>Login</div>
      <div className={styles.textInputInner}>
        <div className={styles.formParent}>
          <div className={styles.form}>
            <UserName wpfnameIconWidth="unset" wpfnameIconAlignSelf="stretch" />
            <Password propWidth="unset" propAlignSelf="stretch" />
            <div className={styles.email}>
              <div className={styles.icbaselineEmailParent}>
                <div className={styles.icbaselineEmail} />
                <img className={styles.vectorIcon} alt="" />
                <div className={styles.mdipassword} />
                <div className={styles.email1}>Email</div>
                <img className={styles.frameChild} alt="" />
              </div>
            </div>
            <div className={styles.email}>
              <div className={styles.icbaselineEmailParent}>
                <div className={styles.icbaselineEmail} />
                <div className={styles.mdipassword} />
                <div className={styles.address1}>Address</div>
                <img className={styles.frameChild} alt="" />
                <img className={styles.entypoaddressIcon} alt="" />
              </div>
            </div>
            <div className={styles.email}>
              <div className={styles.icbaselineEmailParent}>
                <div className={styles.icbaselineEmail} />
                <div className={styles.mdipassword} />
                <div className={styles.phoneNumber1}>Phone number</div>
                <img className={styles.frameChild} alt="" />
                <img className={styles.phphoneFillIcon} alt="" />
              </div>
            </div>
          </div>
          <div className={styles.frameWrapper}>
            <div className={styles.frameParent}>
              <div className={styles.submitButtonWrapper}>
                <button className={styles.submitButton}>
                  <div className={styles.submit}>Submit</div>
                </button>
              </div>
              <div className={styles.alreadyAUserContainer}>
                <span className={styles.notAUser}>{`Not a user?  `}</span>
                <span className={styles.register1}>Register</span>
                <span className={styles.span}>{` `}</span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default TextInput;
