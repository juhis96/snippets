const express = require('express');
const router = express.Router();
const topic = require('../models/topic');
require('dotenv').config();

let categorySequence = ['category1', 'category2', 'category3', 'category3', 'category4', 'category5', 'category6', 'category7'];

// Select a random topic from a specific category and progress to the next category if necessary
router.get('/random/:category', async (req, res, next) => {
    try {
      const { category } = req.params;
      
      // Check if the requested category is the next one in the sequence
      const currentCategoryIndex = categorySequence.indexOf(category);
      const nextCategoryIndex = currentCategoryIndex + 1;
      
      if (currentCategoryIndex === -1) {
        return res.status(400).json({ message: 'Invalid category' });
      }
      
      // Fetch a random topic from the specified category
      const selectedTopic = await topic.aggregate([
        { $match: { status: 'none', category } },
        { $sample: { size: 1 } },
      ]);
      
      if (!selectedTopic.length) {
        return res.json({ message: 'No topics found in the specified category' });
      }
      
      // Update the current topic to 'done' status
      await topic.findOneAndUpdate({ status: 'current' }, { $set: { status: 'done' } });
      
      // Update the selected topic to 'current' status
      await topic.findByIdAndUpdate(selectedTopic[0]._id, { $set: { status: 'current' } });
      
      // Check if the current category was the last one in the sequence
      if (nextCategoryIndex >= categorySequence.length) {
        // Reset to the first category in the sequence
        await topic.updateMany({ category: categorySequence[currentCategoryIndex] }, { $set: { status: 'none' } });
      }
      
      // Progress to the next category
      const nextCategory = categorySequence[nextCategoryIndex];
      
      res.json({ selectedTopic: selectedTopic[0], nextCategory });
    } catch (err) {
      next(err);
    }
  });

//Lock topic by id
router.get('/topics/lock/:id', async (req, res, next) => {
    try {
      await topic.updateMany({ status: 'current' }, { $set: { status: 'done' } });
      const updatedTopic = await topic.findOneAndUpdate({ _id: req.params.id }, { $set: { status: 'current' } }, { new: true });
      res.json(updatedTopic);
    } catch (err) {
      next(err);
    }
  });

//Get a current topic
router.get('/topics/current', (req, res, next) => {
    topic.findOne({"status":"current"})
        .then((data) =>{
            if (data) {
                res.json(data);
            } else {
                return res.json({ topic: "That's all Folks!" });
            }
        }).catch(next);
});

//Roll a new topic
router.get('/topics/roll', (req, res, next) => {
    topic.aggregate([{ $match : { "status" : "none" } },  { $sample: { size: 1 } }]).then((data) => res.json(data)).catch(next);
});


//Get all topics
router.get('/topics', (req, res, next) => {
    topic.find({}).then((data) => res.json(data)).catch(next);
});

//Add a topic
router.post('/topics', (req, res, next) => {
    if (req.body.topic){
        topic.create(req.body).then((data) => res.json(data)).catch(next);
    }else{
        res.json({error: 'Required', });
    }
});

//Update a topic by id
router.post('/topics/:id', (req, res, next) => {
    if (req.body.topic){
        topic.findOneAndUpdate({_id: req.params.id}, req.body).then((data) => res.json(data)).catch(next);
    }else{
        res.json({error: 'Required', });
    }
});

//Get a topic by id
router.get('/topics/:id', (req, res, next) => {
    topic.findOne({_id: req.params.id}).then((data) => res.json(data)).catch(next);
});

//Delete a topic by id
router.delete('/topics/:id', (req, res, next) => {
    topic.findOneAndDelete({_id: req.params.id}).then((data) => res.json(data)).catch(next);
});

module.exports = router;