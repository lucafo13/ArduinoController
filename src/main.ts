import { SerialPort } from 'tauri-plugin-serialplugin-api';

let portaAtiva: SerialPort | null = null;

export const conect = async () => {
    try {
        const ports = await SerialPort.available_ports();
        const nomesDasPortas = Object.keys(ports); 

        if (nomesDasPortas.length === 0) {
            console.log("Nenhum Arduino detectado!");
            return;
        }

        const portaSelecionada = nomesDasPortas[0];
        portaAtiva = new SerialPort({ path: portaSelecionada, baudRate: 9600 });
        await portaAtiva.open();
        
        console.log("Funcionou hein!");
    } catch (error) {
        console.log(`Erro: ${error}`);
    }
};

export const aiBolsonaro = async (com: string) => {
    if (!portaAtiva) {
        console.log("Porta nao conectada");
        return;
    }
    try {
        await portaAtiva.write(com);
        console.log(`Enviado: ${com}`);
    } catch (error) {
        console.log(`Erro ao enviar: ${error}`);
    }
};
