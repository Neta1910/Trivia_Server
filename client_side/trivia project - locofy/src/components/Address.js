import { useMemo } from "react";
import styles from "./Address.module.css";

const Address = ({
  address,
  entypoaddress,
  propPadding,
  propGap,
  propWidth,
}) => {
  const frameDivStyle = useMemo(() => {
    return {
      padding: propPadding,
      gap: propGap,
    };
  }, [propPadding, propGap]);

  const addressStyle = useMemo(() => {
    return {
      width: propWidth,
    };
  }, [propWidth]);

  return (
    <div className={styles.address}>
      <div className={styles.icbaselineEmailParent} style={frameDivStyle}>
        <div className={styles.icbaselineEmail} />
        <div className={styles.icbaselineEmail} />
        <div className={styles.address1} style={addressStyle}>
          {address}
        </div>
        <div className={styles.vectorParent}>
          <img className={styles.frameChild} alt="" src="/vector-2.svg" />
          <img
            className={styles.entypoaddressIcon}
            alt=""
            src={entypoaddress}
          />
        </div>
      </div>
    </div>
  );
};

export default Address;
