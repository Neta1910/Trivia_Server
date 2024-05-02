import { useEffect, useState } from "react"
import { useSocket } from "../componenets/socketContext";
import Constants from "../constents";
const GameScreen = () => {
    const socket = useSocket();
    const [leftQuestions, setLeftQuestions ] = useState(0);
    const [rightAnsowers, setRightAnsowers] = useState(0);
    const [currentQuestion, setCurrentQuestion] = useState('')
    const [currentAnsowers, setCurrentAnsowers] = useState([])

    const getNextQuestion = () => {
        socket.emit("GetQuestion");
        socket.on("GetQuestionResponse", (response) => {
            if (response.status == Constants.WORK_STATUS) {
                setCurrentQuestion(response.question);
                setCurrentAnsowers(response.answers)
            }
            else {
                alert("Somthing went wrong");
            }
        })
    }
    
    return (
        <>
        
        </>
    )
}
