const express = require('express')
const jp = require('jsonpath')
const axios = require('axios')
const cors = require('cors')
const app = express()
const port = 3000

app.use(cors())



const ePerusteAPI = 'https://eperusteet.opintopolku.fi/eperusteet-service/api/external';

async function fetchData(url) {
  try {
    const response = await axios.get(url);
    return response.data;
  } catch (error) {
    console.error('Error fetching data:', error);
    throw new Error('Failed to fetch data');
  }
}

app.get('/api/business/:id', async (req, res) => {
  try {
    const businessData = await fetchData(`http://avoindata.prh.fi/opendata/bis/v1/${req.params.id}`);
    res.json({BusinessId: businessData.results[0].businessId, name: businessData.results[0].name});
    
  } catch (error) {
    //res.status(500).json({ error: error.message });
    res.status(500).json({ error: "Business not found" });
  }
});



app.get('/api/degrees', async (req, res) => {
  try {
    const degreeList = [];
    const degrees = await fetchData(`${ePerusteAPI}/perusteet?sivukoko=100000&voimassa=true`);

    degrees.data.forEach(degree => {
      console.log(degree.nimi.fi);
      diaryNumber = String(degree.diaarinumero);
      diaryYear = parseInt(diaryNumber.substring(diaryNumber.length - 4));
      if(diaryYear>2018 && degree.koulutukset[0]){
        degreeList.push({_id: degree.id, diaryNumber: degree.diaarinumero, eduCodeValue: degree.koulutukset[0].koulutuskoodiArvo, name: {fi: degree.nimi.fi, sv: degree.nimi.sv, en: degree.nimi.en}});
      }
    });

    res.json(degreeList);

  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

app.get('/api/degree/:id', async (req, res) => {
  try {
    const degreeData = await fetchData(`${ePerusteAPI}/peruste/${req.params.id}`);
    const degreeUnits = await fetchData(`${ePerusteAPI}/peruste/${req.params.id}/tutkinnonOsat`);
    let unitList = [];

    degreeUnits.forEach(unit => {
      let modules = jp.query(unit, '$..arviointi.arvioinninKohdealueet[*]');
      //let modules = arviointi.arvioinninKohdealueet;

      console.log(unit);
      
      let assessmentList = [];

      modules.forEach(module => {
        let criteria = module.arvioinninKohteet[0].osaamistasonKriteerit[0].kriteerit;
        let criteriaList = [];

        criteria.forEach(criterion => {
          criteriaList.push({_id: criterion._id, fi: criterion.fi, sv: criterion.sv, en: criterion.en});
        });

        assessmentList.push({_id: module.koodi.id, name: {fi: module.otsikko.fi, sv: module.otsikko.sv, en: module.otsikko.en}, criteria: criteriaList});
      });

      unitList.push({_id: unit.id, name: {fi: unit.nimi.fi, sv: unit.nimi.sv, en: unit.nimi.en}, assessments: assessmentList});

    });

    const degree = {
      _id: req.params.id,
      name: {fi: degreeData.nimi.fi, sv: degreeData.nimi.sv, en: degreeData.nimi.en},
      eduCodeValue: degreeData.koulutukset[0].koulutuskoodiArvo,
      diaryNumber: degreeData.diaarinumero,
      regulationDate: degreeData.paatospvm,
      transitionEnds: degreeData.siirtymaPaattyy,
      validFrom: degreeData.voimassaoloAlkaa,
      expiry: degreeData.voimassaoloLoppuu,
      examInfoURL: `https://eperusteet.opintopolku.fi/#/fi/ammatillinen/${req.params.id}/tiedot`,
      description: {fi: degreeData.kuvaus.fi, sv: degreeData.kuvaus.sv, en: degreeData.kuvaus.en},
      units: unitList,
    };

    res.json(degree);

  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});


app.get('/', async (req, res) => {
  const bgUrls = ['https://thefluffingtonpost.com/wp-content/uploads/2014/01/tumblr_myvw3gAam81qdedm3o1_1280.jpg',
  'https://i.pinimg.com/originals/17/41/7e/17417ee95ff3a5907b9a1edc60292a4d.jpg',
  'https://www.thetimes.co.uk/imageserver/image/%2Fmethode%2Ftimes%2Fprod%2Fweb%2Fbin%2Ffeafda08-2146-11ec-8cb7-e60ba8dbca61.jpg',
  'https://live.staticflickr.com/7916/46419794735_ab291e6c4e_b.jpg',
  'https://images.fineartamerica.com/images-medium-large-5/giant-otter-max-waugh.jpg',
  'https://i.imgur.com/f9lsO3V.jpg',
  'https://i.ytimg.com/vi/dA0kwaPNZ8k/maxresdefault.jpg',
  'https://i.imgur.com/FTpurUI.jpeg',
  'https://media.wired.com/photos/5932368352d99d6b984dd15f/191:100/w_1280,c_limit/giant-otters-ft.jpg']; 
  res.send(`<body style="background-image: url('${bgUrls[Math.floor((Math.random()*bgUrls.length))]}');
  background-repeat: no-repeat; background-size: 100% 100%;text-align:center;">
  <h1 style="color:red;">SAUKKO API</h1></body>`);
});


app.get('/api/degrees/temporary', async (req, res) => {
  try {
    const degreeList = [];
    const diaarinumeroLista = ['OPH-3837-2022', 'OPH-5063-2021', 'OPH-5030-2021', 'OPH-1825-2021', 'OPH-1807-2021'];
    const degrees = await fetchData(`https://eperusteet.opintopolku.fi/eperusteet-service/api/external/perusteet?sivukoko=100000&voimassa=true`);

    degrees.data.forEach(degree => {
      if(diaarinumeroLista.includes(degree.diaarinumero)){
        console.log(degree.nimi.fi);
        degreeList.push({_id: degree.id, diaryNumber: degree.diaarinumero, eduCodeValue: degree.koulutukset[0].koulutuskoodiArvo, name: {fi: degree.nimi.fi, sv: degree.nimi.sv, en: degree.nimi.en}});
      }
    });

    res.json(degreeList);

  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});


app.get('/diaarinumero/:nro', async (req, res) => {
    try {
        const perusteet = await fetchData(`https://eperusteet.opintopolku.fi/eperusteet-service/api/external/perusteet?diaarinumero=${req.params.nro}`);
        var perusteNimi = perusteet.data[0].nimi.fi;
        var koulutuskoodiArvo = perusteet.data[0].koulutukset[0].koulutuskoodiArvo;
        var diaarinumero = perusteet.data[0].diaarinumero;
        var perusteId = perusteet.data[0].id;

        const peruste = await fetchData(`https://eperusteet.opintopolku.fi/eperusteet-service/api/external/peruste/${perusteId}`);
        var paatospvm = peruste.paatospvm;
        var siirtymaPaattyy = peruste.siirtymaPaattyy;
        var voimassaoloAlkaa = peruste.voimassaoloAlkaa;
        var voimassaoloLoppuu = peruste.voimassaoloLoppuu;
        var perusteKuvaus = peruste.kuvaus.fi;
        var perusteLinkki = `https://eperusteet.opintopolku.fi/#/fi/ammatillinen/${perusteId}/tiedot`;
        
        const options = { day: 'numeric', month: 'numeric', year: 'numeric' };
        var paatos = new Date(paatospvm);
        var voimaantulo = new Date(voimassaoloAlkaa);

        const formattedDate = paatos.toLocaleDateString(undefined, options);

        console.log(formattedDate);

        console.log(paatos.toString());
        console.log(voimaantulo.toString());


        //tutkinnonOsat

        const tknOsat = await fetchData(`https://eperusteet.opintopolku.fi/eperusteet-service/api/external/peruste/${perusteId}/tutkinnonOsat`);

        let ePer = [];

        tknOsat.forEach(xoo => {
          var arvioinninKohteet = jp.query(xoo, '$..arviointi.arvioinninKohdealueet[*]');

          var lista = [];
  
          arvioinninKohteet.forEach(index => {
            //console.log(index);
            //console.log(jp.query(index, '$..otsikko.fi'));
            var indexOtsikko = index.otsikko.fi;
            //console.log(index.otsikko.fi);
            var kriteerit = index.arvioinninKohteet[0].osaamistasonKriteerit[0].kriteerit;
  
            var indexKriteerit = [];
  
            kriteerit.forEach(kriteeri => {
              //console.log(kriteeri.fi);
              indexKriteerit.push(kriteeri.fi);
            });
            //console.log(jp.query(index.arvioinninKohteet, '$.osaamistasonKriteerit.otsikko.fi'));
            //console.log(jp.query());
            lista.push({nimi: indexOtsikko, kriteerit: indexKriteerit});
          });

          
          ePer.push({osanNimi: xoo.nimi.fi, osanArviointi: lista});

        });

        /*
        tknOsat.forEach(xoo => {
          ePer.push(xoo.nimi.fi);
        });

          var arvioinninKohteet = jp.query(peruste, '$.tutkinnonOsat..arviointi.arvioinninKohdealueet[*]');

          var arvioinninKohteet = jp.query(peruste, '$.arviointi.arvioinninKohdealueet[*]');

          var lista = [];
  
          arvioinninKohteet.forEach(index => {
            //console.log(index);
            //console.log(jp.query(index, '$..otsikko.fi'));
            var indexOtsikko = index.otsikko.fi;
            //console.log(index.otsikko.fi);
            var kriteerit = index.arvioinninKohteet[0].osaamistasonKriteerit[0].kriteerit;
  
            var indexKriteerit = [];
  
            kriteerit.forEach(kriteeri => {
              //console.log(kriteeri.fi);
              indexKriteerit.push(kriteeri.fi);
            });
            //console.log(jp.query(index.arvioinninKohteet, '$.osaamistasonKriteerit.otsikko.fi'));
            //console.log(jp.query());
            lista.push({nimi: indexOtsikko, kriteerit: indexKriteerit});
          });
        */

        var ePeruste = {
          id: perusteId,
          nimi: perusteNimi,
          koodi: koulutuskoodiArvo,
          diaarinumero: diaarinumero,
          paatospvm: paatospvm,
          siirtymaPaatty: siirtymaPaattyy,
          voimassaoloAlkaa: voimassaoloAlkaa,
          voimassaoloLoppuu: voimassaoloLoppuu,
          lisatietoLinkki: perusteLinkki,
          //kuvaus: perusteKuvaus,
          //tutkinnonOsat: lista,
          tutkinnonOsat: ePer,
      };


        res.json(ePeruste);

        /*
        const tutkinnonOsaOtsikot = jp.query(peruste, '$.tutkinnonOsat..nimi.fi');
        const tutkinnonOsaArviointi = jp.query(peruste, '$.tutkinnonOsat..arviointi..otsikko.fi');
        $.tutkinnonOsat..arviointi.arvioinninKohdealueet
        $.tutkinnonOsat..arviointi.arvioinninKohdealueet..otsikko
        $.tutkinnonOsat..arviointi.arvioinninKohdealueet..arvioinninKohteet..osaamistasonKriteerit
        jp.query(peruste, '$.tutkinnonOsat')
        */

    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.listen(port, () => {
  console.log(`Listening on port ${port}`)
})