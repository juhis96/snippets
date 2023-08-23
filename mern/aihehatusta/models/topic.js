const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const TopicSchema = new Schema({
    topic: {
        type: String,
        required: true,
    },
    status: String,
    category: String,
});

const Topic = mongoose.model('topic', TopicSchema)

module.exports = Topic;