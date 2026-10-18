
import { conect, aiBolsonaro } from "./main.ts";
import "./App.css";

function App() {

 
  return(
    <main className="resenha">
      <div>
        <h1>CLique abaixo para conectar no arduino </h1>
        
        <button onClick={conect}>Conectar</button>
      </div>
      <p  >Clique nos botões a seguir para acionar as respectivas sequencias: </p>
      <div className="izi">
       
        <button onClick={() => {aiBolsonaro("1")}}>Neurônio em repouso</button>
        <button onClick={() => {aiBolsonaro("2")}}>Impulso nervoso</button>
        <button onClick={() => {aiBolsonaro("3")}}>Lesão medular</button>
        <button onClick={() => {aiBolsonaro("4")}}>Polilaminina</button>
      
      </div>
      <h1>Feito com Preguiça</h1>
      <p>Davi lucas</p>
    </main>
  )
  
}

export default App;
