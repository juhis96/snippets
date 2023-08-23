import React, { Component } from 'react';
import axios from 'axios';
import Input from './Input';
import ListTopic from './ListTopic';
import RollTopic from './RollTopic';

class Topic extends Component {
  state = {
    topics: [],
  };

  componentDidMount() {
    this.getTopics();
  }


  getTopics = () => {
    axios
      .get('/api/topics')
      .then((res) => {
        if (res.data) {
          this.setState({
            topics: res.data,
          });
        }
      })
      .catch((err) => console.log(err));
  };

  deleteTopic = (id) => {
    axios
      .delete(`/api/topics/${id}`)
      .then((res) => {
        if (res.data) {
          this.getTopics();
        }
      })
      .catch((err) => console.log(err));
  };

  render() {
    let { topics } = this.state;

    return (
      <div>
        <h1>Topic Manager</h1>
        <Input getTopics={this.getTopics} />
        <ListTopic topics={topics} deleteTopic={this.deleteTopic} />
      </div>
    );
  }
}

export default Topic;