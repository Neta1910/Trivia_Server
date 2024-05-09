import UserName from "./UserName";
import Password from "./Password";
import Address from "./Address";
import styles from "./TextInput1.module.css";

const TextInput1 = () => {
  return (
    <div className={styles.textInput}>
      <div className={styles.register}>Register</div>
      <div className={styles.register1}>
        <div className={styles.form}>
          <UserName />
          <Password />
          <div className={styles.email}>
            <div className={styles.icbaselineEmailParent}>
              <div className={styles.icbaselineEmail} />
              <div className={styles.icbaselineEmail} />
              <div className={styles.email1}>Email</div>
              <div className={styles.vectorParent}>
                <img className={styles.vectorIcon} alt="" src="/vector-1.svg" />
                <img className={styles.frameChild} alt="" src="/vector-2.svg" />
              </div>
            </div>
          </div>
          <Address address="Address" entypoaddress="/entypoaddress.svg" />
          <Address
            address="Phone number"
            entypoaddress="/phphonefill.svg"
            propPadding="var(--padding-5xs) var(--padding-5xl) var(--padding-6xs) var(--padding-377xl)"
            propGap="83px"
            propWidth="330px"
          />
        </div>
      </div>
      <div className={styles.logoContainer}>
        <div className={styles.submitBtnParent}>
          <div className={styles.submitBtn}>
            <button className={styles.submitButton}>
              <div className={styles.submit}>Submit</div>
            </button>
          </div>
          <div className={styles.alreadyAUserContainer}>
            <span>{`already a user? `}</span>
            <span className={styles.logIn}>{`log in `}</span>
          </div>
        </div>
      </div>
    </div>
  );
};

export default TextInput1;
