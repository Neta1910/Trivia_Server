import styles from "./Login.module.css";

const Login = () => {
  return (
    <div className={styles.login}>
      <div className={styles.textInput}>
        <div className={styles.register}>Login</div>
        <div className={styles.textInputInner}>
          <div className={styles.formParent}>
            <div className={styles.form}>
              <div className={styles.userName}>
                <div className={styles.userNameParent}>
                  <div className={styles.userName1}>User name</div>
                  <div className={styles.submitButtonContainer}>
                    <div className={styles.wpfnameParent}>
                      <img
                        className={styles.wpfnameIcon}
                        alt=""
                        src="/vector-2.svg"
                      />
                      <img
                        className={styles.wpfnameIcon1}
                        alt=""
                        src="/wpfname.svg"
                      />
                    </div>
                  </div>
                </div>
              </div>
              <div className={styles.userName}>
                <div className={styles.mdipasswordParent}>
                  <div className={styles.mdipassword} />
                  <div className={styles.passwordWrapper}>
                    <div className={styles.createdByYoel}>Password</div>
                  </div>
                  <div className={styles.vectorParent}>
                    <img
                      className={styles.vectorIcon}
                      alt=""
                      src="/vector.svg"
                    />
                    <img
                      className={styles.wpfnameIcon}
                      alt=""
                      src="/vector-2.svg"
                    />
                  </div>
                </div>
              </div>
              <div className={styles.email}>
                <div className={styles.icbaselineEmailParent}>
                  <div className={styles.icbaselineEmail} />
                  <img className={styles.vectorIcon1} alt="" />
                  <div className={styles.mdipassword1} />
                  <div className={styles.email1}>Email</div>
                  <img className={styles.frameItem} alt="" />
                </div>
              </div>
              <div className={styles.email}>
                <div className={styles.icbaselineEmailParent}>
                  <div className={styles.icbaselineEmail} />
                  <div className={styles.mdipassword1} />
                  <div className={styles.address1}>Address</div>
                  <img className={styles.frameItem} alt="" />
                  <img className={styles.entypoaddressIcon} alt="" />
                </div>
              </div>
              <div className={styles.email}>
                <div className={styles.icbaselineEmailParent}>
                  <div className={styles.icbaselineEmail} />
                  <div className={styles.mdipassword1} />
                  <div className={styles.phoneNumber1}>Phone number</div>
                  <img className={styles.frameItem} alt="" />
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
      <img className={styles.logo1Icon} alt="" src="/logo-1.svg" />
      <div className={styles.createdByYoelWeisbergAndNWrapper}>
        <div className={styles.createdByYoel}>
          Created by Yoel weisberg and neta orevi
        </div>
      </div>
    </div>
  );
};

export default Login;
