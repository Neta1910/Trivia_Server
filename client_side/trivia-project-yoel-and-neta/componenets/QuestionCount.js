import React, { useEffect, useState } from 'react';
import styles from '../styles/QuestionCount.module.css'; // Assuming the CSS module file is named QuestionCount.module.css

function QuestionCount({ count }) {
    const [triggerAnimation, setTriggerAnimation] = useState(false);

    useEffect(() => {
        setTriggerAnimation(true);
        const timer = setTimeout(() => setTriggerAnimation(false), 500); // Animation lasts for 500 ms
        return () => clearTimeout(timer);
    }, [count]);

    return (
        <div className={triggerAnimation ? `${styles.counter} ${styles.animate}` : styles.counter}>
            Question Count: {count}
        </div>
    );
}

export default QuestionCount;
