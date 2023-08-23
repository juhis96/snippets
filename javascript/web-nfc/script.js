function sendResult(message) {
  document.getElementById('result').innerHTML += message + '<br>';
}

// Check if Web NFC is supported
if ('NDEFReader' in window) {
  const scanButton = document.getElementById('scanButton');

  scanButton.addEventListener('click', async () => {
    try {
      const ndef = new NDEFReader();
      await ndef.scan();
      sendResult("Waiting for NFC...");

      ndef.addEventListener("readingerror", () => {
        sendResult("error: Failed to read!");
      });

      ndef.addEventListener("reading", ({ message, serialNumber }) => {
        sendResult(`Serial Number: ${serialNumber} / Records: ${message.records.length}`);
      });
    } catch (error) {
      sendResult("error: " + error);
    }
  });
} else {
  document.getElementById('result').innerText = 'error: Web NFC is not supported on this device/browser.';
}
