import { useEffect } from "react";
import {
  Routes,
  Route,
  useNavigationType,
  useLocation,
} from "react-router-dom";
import Register from "./pages/Register";
import Statistics from "./pages/Statistics";
import Menu from "./pages/Menu";
import GameBoard from "./pages/GameBoard";
import WaitRoom from "./pages/WaitRoom";
import JoinRoom from "./pages/JoinRoom";
import Login from "./pages/Login";
import CreateRoom from "./pages/CreateRoom";
import Logout from "./components/logout";

function App() {
  const action = useNavigationType();
  const location = useLocation();
  const pathname = location.pathname;

  useEffect(() => {
    if (action !== "POP") {
      window.scrollTo(0, 0);
    }
  }, [action, pathname]);

  useEffect(() => {
    let title = "";
    let metaDescription = "";

    switch (pathname) {
      case "/":
        title = "";
        metaDescription = "";
        break;
      case "/statistics":
        title = "";
        metaDescription = "";
        break;
      case "/menu":
        title = "";
        metaDescription = "";
        break;
      case "/game-board":
        title = "";
        metaDescription = "";
        break;
      case "/wait-room":
        title = "";
        metaDescription = "";
        break;
      case "/join-room":
        title = "";
        metaDescription = "";
        break;
      case "/login":
        title = "";
        metaDescription = "";
        break;
      case "/create-room":
        title = "";
        metaDescription = "";
        break;
      case "/logout":
        title = "";
        metaDescription = "";
        break;
    }

    if (title) {
      document.title = title;
    }

    if (metaDescription) {
      const metaDescriptionTag = document.querySelector(
        'head > meta[name="description"]'
      );
      if (metaDescriptionTag) {
        metaDescriptionTag.content = metaDescription;
      }
    }
  }, [pathname]);

  return (
    <Routes>
      <Route path="/" element={<Register />} />
      <Route path="/statistics" element={<Statistics />} />
      <Route path="/menu" element={<Menu />} />
      <Route path="/game-board" element={<GameBoard />} />
      <Route path="/wait-room" element={<WaitRoom />} />
      <Route path="/join-room" element={<JoinRoom />} />
      <Route path="/login" element={<Login />} />
      <Route path="/create-room" element={<CreateRoom />} />
      <Route path="/logout" element={<Logout />} />
    </Routes>
  );
}
export default App;
