import styles from "./InformationCardInWait.module.css";

const InformationCard = ({ text, Icon }) => {
  return (
    <div className={styles.information}>
      <div className={styles.vectorWrapper}>
        <img className={styles.vectorIcon} loading="lazy" alt="" src={Icon} />
      </div>
      <h3 className={styles.thereIsXContainer}>
        <p className={styles.thereIsXQuestions}>
          <span className={styles.thereIsX}>{text}</span>
        </p>
      </h3>
    </div>
  );
};

export default InformationCard;
