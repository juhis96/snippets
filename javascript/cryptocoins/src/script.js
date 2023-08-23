document.addEventListener("DOMContentLoaded", () => {
    fetchAndDisplayCoins(); // Fetch and display coins immediately
    setInterval(fetchAndDisplayCoins, 60000); // Refresh every 1 minute (60,000 milliseconds)
});

async function fetchAndDisplayCoins() {
    const response = await fetch("https://www.worldcoinindex.com/apiservice/v2getmarkets?key=APIKEYHERE&fiat=usd"); // Replace with your actual API URL
    const data = await response.json();

    const markets = data.Markets.flat(); // Flatten the nested arrays

    // Sort the markets by Volume_24h in descending order
    markets.sort((a, b) => b.Volume_24h - a.Volume_24h);

    const coinList = document.getElementById("coinList");
    coinList.innerHTML = ''; // Clear the previous list

    // Display the top 5 coins
    for (let i = 0; i < 5 && i < markets.length; i++) {
        const coin = markets[i];
        const li = document.createElement("li");
        
        // Convert Unix timestamp to a human-readable date and time format
        const timestamp = new Date(coin.Timestamp * 1000);
        const formattedTimestamp = timestamp.toLocaleString();
        
        li.innerHTML = `
            <span class="coin-label">${coin.Name}</span>
            <span class="coin-price">$${coin.Price.toFixed(2)}</span>
            <span class="coin-volume">${coin.Volume_24h.toFixed(2)}</span>
            <span class="coin-timestamp">${formattedTimestamp}</span>
        `;
        
        coinList.appendChild(li);
    }
}