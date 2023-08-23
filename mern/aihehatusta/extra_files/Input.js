import React, { Component } from 'react';
import axios from 'axios';

class Input extends Component {
  state = {
    topic: '',
  };

  addTopic = () => {
    const newTopic = { topic: this.state.topic };

    if (newTopic.topic && newTopic.topic.length > 0) {
      axios
        .post('/api/topics', newTopic)
        .then((res) => {
          if (res.data) {
            this.props.gettopics();
            this.setState({ topic: '' });
          }
        })
        .catch((err) => console.log(err));
    } else {
      console.log('input field required');
    }
  };

  handleChange = (e) => {
    this.setState({
      topic: e.target.value,
    });
  };

  render() {
    let { topic } = this.state;
    return (
      <div>
        <input type="text" onChange={this.handleChange} value={topic} />
        <button onClick={this.addTopic}>add topic</button>
      </div>
    );
  }
}

export default Input;