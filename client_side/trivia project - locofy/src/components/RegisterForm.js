import UserNameInput from "./UserNameInput";
import styles from "./RegisterForm.module.css";

const RegisterForm = () => {
  return (
    <div className={styles.registerForm}>
      <div className={styles.register}>Register</div>
      <div className={styles.mdipassword} />
      <div className={styles.frameParent}>
        <div className={styles.usernameInputParent}>
          <UserNameInput placeHolder="User name" icon="/wpfname.svg"/>
          <UserNameInput placeHolder="Password" icon="/email-icon.svg"/>
          {/* <div className={styles.userNameParent}>
            <div className={styles.userName}>Password</div>
            <div className={styles.frameWrapper}>
              <div className={styles.vectorParent}>
                <img className={styles.frameChild} alt="" src="/vector-2.svg" />
                <img
                  className={styles.emailIcon}
                  alt=""
                  src="/email-icon.svg"
                />
              </div>
            </div>
          </div> */}
          <div className={styles.emailParent}>
            <div className={styles.email}>Email</div>
            <div className={styles.frameWrapper}>
              <div className={styles.vectorGroup}>
                <img className={styles.frameChild} alt="" src="/vector-2.svg" />
                <img
                  className={styles.icbaselineEmailIcon}
                  alt=""
                  src="/icbaselineemail.svg"
                />
              </div>
            </div>
          </div>
          <div className={styles.addressParent}>
            <div className={styles.address}>Address</div>
            <div className={styles.frameWrapper}>
              <div className={styles.vectorContainer}>
                <img className={styles.frameChild} alt="" src="/vector-2.svg" />
                <img
                  className={styles.entypoaddressIcon}
                  alt=""
                  src="/entypoaddress.svg"
                />
              </div>
            </div>
          </div>
          <div className={styles.phoneNumberParent}>
            <div className={styles.phoneNumber}>Phone number</div>
            <div className={styles.frameWrapper}>
              <div className={styles.vectorContainer}>
                <img className={styles.frameChild} alt="" src="/vector-2.svg" />
                <img
                  className={styles.entypoaddressIcon}
                  alt=""
                  src="/phphonefill.svg"
                />
              </div>
            </div>
          </div>
        </div>
        <div className={styles.frameWrapper2}>
          <div className={styles.frameGroup}>
            <div className={styles.submitButtonWrapper}>
              <div className={styles.submitButton}>
                <div className={styles.submit}>Submit</div>
              </div>
            </div>
            <div className={styles.alreadyAUserContainer}>
              <span>{`already a user? `}</span>
              <span className={styles.logIn}>{`log in `}</span>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default RegisterForm;
