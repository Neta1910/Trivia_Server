import styles from "./UserNameInput.module.css";
import { useState } from "react";
import SliderInput from "./SlliderInput";
const TextInput = ({
  placeHolder,
  icon,
  type = "text",
  setter,
  pattern = "*",
  title = "",
  min = 0,
  max = 0,
}) => {
  const [value, setValue] = useState(type === "range" ? (max + min) / 2 : "");
  const [showPassword, setShowPassword] = useState(false);

  const handleChange = (event) => {
    const newValue = event.target.value;
    setValue(newValue);
    setter(newValue);
  };

  const togglePasswordVisibility = () => {
    setShowPassword((prevShowPassword) => !prevShowPassword);
  };

  return (
    <div className={styles.usernameInput}>
      <div className={styles.userNameParent}>
        {type !== "range" ? (
          <input
            className={styles.userName}
            placeholder={placeHolder}
            type={showPassword ? "text" : type}
            onChange={handleChange}
            pattern={pattern}
            title={title}
            value={value}
            required
          />
        ) : (
          <SliderInput setter={setter} min={min} max={max} title={placeHolder} />
        )}
        <div className={styles.inputWrapper}>
          <div className={styles.vectorParent} onClick={togglePasswordVisibility}>
            <img className={styles.frameChild} alt="" src="/vector-2.svg" />
            <img className={styles.wpfnameIcon} alt="" src={icon} />
          </div>
        </div>
      </div>
    </div>
  );
};

export default TextInput;
