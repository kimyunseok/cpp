package com.inhamall.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import com.inhamall.model.User;
import com.inhamall.util.DBUtil;

public class UserDao {

	private Connection connection;

	public UserDao() {
		connection = DBUtil.getConnection();
	}

	public void addUser(User user) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("insert into user_table (usertype, id, password, username, dob, sex, contact, address, email) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");
			// Parameters start with 1
			preparedStatement.setInt(1, 0);
			preparedStatement.setString(2, user.getId());
			preparedStatement.setString(3, user.getPassword());
			preparedStatement.setString(4, user.getUsername());
			preparedStatement.setString(5, user.getDob());
			preparedStatement.setString(6, user.getSex());
			preparedStatement.setString(7, user.getContact());
			preparedStatement.setString(8, user.getAddress());
			preparedStatement.setString(9, user.getEmail());
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void deleteUser(int useridx) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("delete from user_table where useridx=?");
			// Parameters start with 1
			preparedStatement.setInt(1, useridx);
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void updateUser(User user) {
		try {
			PreparedStatement preparedStatement = connection
					.prepareStatement("update user_table set usertype=?, id=?, password=?, username=?, dob=?, sex=?," +
							"contact=?, address=?, email=? where UserIdx=?");
			// Parameters start with 1
			preparedStatement.setInt(1, user.getUsertype());
			preparedStatement.setString(2, user.getId());
			preparedStatement.setString(3, user.getPassword());
			preparedStatement.setString(4, user.getUsername());
			preparedStatement.setString(5, user.getDob());
			preparedStatement.setString(6, user.getSex());
			preparedStatement.setString(7, user.getContact());
			preparedStatement.setString(8, user.getAddress());
			preparedStatement.setString(9, user.getEmail());
			preparedStatement.setInt(10, user.getUseridx());
			preparedStatement.executeUpdate();

		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public List<User> getAllUsers() {
		List<User> users = new ArrayList<User>();
		try {
			Statement statement = connection.createStatement();
			ResultSet rs = statement.executeQuery("select * from user_table");
			while (rs.next()) {
				User user = new User();
				user.setUseridx(rs.getInt("useridx"));
				user.setUsertype(rs.getInt("usertype"));
				user.setId(rs.getString("id"));
				user.setPassword(rs.getString("password"));
				user.setUsername(rs.getString("username"));
				user.setDob(rs.getString("dob"));
				user.setSex(rs.getString("sex"));
				user.setContact(rs.getString("contact"));
				user.setAddress(rs.getString("address"));
				user.setEmail(rs.getString("email"));
				users.add(user);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return users;
	}
	
	public User getUserByIdx(int userIdx) {
		User user = new User();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from user_table where useridx=?");
			preparedStatement.setInt(1, userIdx);
			ResultSet rs = preparedStatement.executeQuery();
			
			if (rs.next()) {
				user.setUseridx(rs.getInt("useridx"));
				user.setUsertype(rs.getInt("usertype"));
				user.setId(rs.getString("id"));
				user.setPassword(rs.getString("password"));
				user.setUsername(rs.getString("username"));
				user.setDob(rs.getString("dob"));
				user.setSex(rs.getString("sex"));
				user.setContact(rs.getString("contact"));
				user.setAddress(rs.getString("address"));
				user.setEmail(rs.getString("email"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return user;
	}
	
	public User getUserById(String userId) {
		User user = new User();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from user_table where id=?");
			preparedStatement.setString(1, userId);
			ResultSet rs = preparedStatement.executeQuery();
			
			if (rs.next()) {
				user.setUseridx(rs.getInt("useridx"));
				user.setUsertype(rs.getInt("usertype"));
				user.setId(rs.getString("id"));
				user.setPassword(rs.getString("password"));
				user.setUsername(rs.getString("username"));
				user.setDob(rs.getString("dob"));
				user.setSex(rs.getString("sex"));
				user.setContact(rs.getString("contact"));
				user.setAddress(rs.getString("address"));
				user.setEmail(rs.getString("email"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return user;
	}
	
	public User Login(String userId, String userPassword) {
		User user = null;
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from user_table where id=? and password=?");
			preparedStatement.setString(1, userId);
			preparedStatement.setString(2, userPassword);
			ResultSet rs = preparedStatement.executeQuery();
			
			if (rs.next()) {
				user = new User();
				user.setUseridx(rs.getInt("useridx"));
				user.setUsertype(rs.getInt("usertype"));
				user.setId(rs.getString("id"));
				user.setPassword(rs.getString("password"));
				user.setUsername(rs.getString("username"));
				user.setDob(rs.getString("dob"));
				user.setSex(rs.getString("sex"));
				user.setContact(rs.getString("contact"));
				user.setAddress(rs.getString("address"));
				user.setEmail(rs.getString("email"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return user;
	}
	
	public boolean searchId(String id) { 
		PreparedStatement pstmt=null; 
		ResultSet rs=null; boolean 
		flag=false; 
		String sql="select * from user_table where id=?"; 
		try { 
			pstmt=connection.prepareStatement(sql); 
			pstmt.setString(1, id); 
			rs=pstmt.executeQuery(); 
			if(rs.next()) { 
				flag=true; 
				} 
			} catch (SQLException e) { 
				// TODO Auto-generated catch block 
				e.printStackTrace(); }
		finally { 
			try { 
				rs.close(); 
				pstmt.close(); 
				} catch (SQLException e) { 
					// TODO Auto-generated catch block 
					e.printStackTrace(); 
					} 
			} 
		return flag; 
		}
	
	public List<User> getUserByEC(String email, String contact) {
		List<User> users = new ArrayList<User>();
		try {
			PreparedStatement preparedStatement = connection.
					prepareStatement("select * from user_table where email=? and contact=?");
			preparedStatement.setString(1, email);
			preparedStatement.setString(2, contact);
			ResultSet rs = preparedStatement.executeQuery();
			
			while (rs.next()) {
				User user = new User();
				user.setUseridx(rs.getInt("useridx"));
				user.setUsertype(rs.getInt("usertype"));
				user.setId(rs.getString("id"));
				user.setPassword(rs.getString("password"));
				user.setUsername(rs.getString("username"));
				user.setDob(rs.getString("dob"));
				user.setSex(rs.getString("sex"));
				user.setContact(rs.getString("contact"));
				user.setAddress(rs.getString("address"));
				user.setEmail(rs.getString("email"));
				users.add(user);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return users;
}
	
}
