import styles from "./UserNameInput.module.css";

const TextInput = ({ placeHolder, icon, type = "text", setter, pattern="*", title=""}) => {
  const handleChange = (event) => {
    setter(event.target.value);
  };
  return (
    <div className={styles.usernameInput}>
      <div className={styles.userNameParent}>
        <textarea className={styles.userName} placeholder={placeHolder} type={type} onChange={handleChange} pattern={pattern} title={title} required/>
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

export default TextInput;
