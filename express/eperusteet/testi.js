const express = require('express');
const app = express();

async function fetchData(url) {
    try {
      const response = await fetch(url);
      if (!response.ok) {
        throw new Error('Failed to fetch data');
      }
      const data = await response.json();
      return data;
    } catch (error) {
      console.error('Error fetching data:', error);
      throw new Error('Failed to fetch data');
    }
  }

// Custom function to filter and extract "fi" values along with their parent objects
function filterFiWithParent(jsonData) {
  const results = [];
  function traverse(obj, parent = null) {
    if (obj && typeof obj === 'object') {
      if (obj.fi) {
        results.push({ parent, fi: obj.fi });
      }
      for (const key in obj) {
        traverse(obj[key], obj);
      }
    }
  }
  traverse(jsonData);
  return results;
}

// Custom recursive function to filter and extract "fi" values along with their paths
function extractFiWithPaths(obj, path = '') {
    const results = [];
    if (obj && typeof obj === 'object') {
      for (const key in obj) {
        if (key === 'fi') {
          results.push({ path: path + '.' + key, fi: obj[key] });
        } else {
          results.push(...extractFiWithPaths(obj[key], path + '.' + key));
        }
      }
    }
    return results;
  }

  
// Custom recursive function to extract "fi" values
function extractFiValues(obj) {
    const results = [];
    if (obj && typeof obj === 'object') {
      for (const key in obj) {
        if (key === 'fi') {
          results.push(obj[key]);
        } else {
          results.push(...extractFiValues(obj[key]));
        }
      }
    }
    return results;
  }

// Route to get the filtered "fi" values with their parent objects
app.get('/fiValues/:id', async (req, res) => {
  const degreeUnits = await fetchData(`https://eperusteet.opintopolku.fi/eperusteet-service/api/external/peruste/${req.params.id}/tutkinnonOsat`);
  const filteredData = extractFiValues(degreeUnits);
  res.json(filteredData);
});

// Start the server
const port = 3000;
app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});