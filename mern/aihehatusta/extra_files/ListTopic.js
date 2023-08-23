import React from 'react';

const ListTopic = ({ topics, deleteTopic }) => {
  return (
    <ul>
      {topics && topics.length > 0 ? (
        topics.map((topic) => {
          return (
            <li key={topic._id} onClick={() => deleteTopic(topic._id)}>
              {topic.topic}
            </li>
          );
        })
      ) : (
        <li>No topics(s) left</li>
      )}
    </ul>
  );
};

export default ListTopic;