/* jshint indent: 2 */

module.exports = function(sequelize, DataTypes) {
  return sequelize.define('users', {
    name: {
      type: DataTypes.CHAR(10),
      allowNull: true
    },
    id: {
      type: DataTypes.CHAR(10),
      allowNull: false,
      primaryKey: true
    },
    pw: {
      type: DataTypes.CHAR(20),
      allowNull: true
    },
    email: {
      type: DataTypes.CHAR(20),
      allowNull: true
    }
  }, {
    timestamps: false,
    tableName: 'users'
  });
};
