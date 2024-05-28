import styles from "./UserNameInput.module.css";
import { useState } from "react";
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
  const handleChange = (event) => {
    setValue(event.target.value);
    setter(event.target.value);
  };

  // Initialize state for the slider value
  const [value, setValue] = useState((max + min) / 2);

  return (
      <div className={styles.usernameInput}>
        <div className={styles.userNameParent}>
          {type === "range" ? (
            <>
              {/* Display the current value above the slider */}
              <div className={styles.sliderValue}>{value}</div>
            </>
          ) : null}

          <input
            className={styles.userName}
            placeholder={placeHolder}
            type={type}
            onChange={handleChange}
            pattern={pattern}
            title={title}
            min={min}
            max={max}
            value={value}
            required
          />
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
