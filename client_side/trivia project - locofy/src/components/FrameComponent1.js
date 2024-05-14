import styles from "./FrameComponent1.module.css";
import InformationCard from "./InformationCardInWait";

const TopPart = ({amountOfQuestions, timout}) => {
  return (
    <section className={styles.informationParent}>
      <InformationCard 
        text={`There are ${amountOfQuestions} questions in this room`}
        Icon={"/vector.svg"}
      />
      
      <img
        className={styles.frameChild}
        loading="lazy"
        alt=""
        src="/vector-8.svg"
      />
      
      <InformationCard 
        text={`You have ${timout} seconds to answer each question`}
        Icon={"/mingcutetimefill.svg"}
      />
    </section>
  );
};

export default TopPart;
