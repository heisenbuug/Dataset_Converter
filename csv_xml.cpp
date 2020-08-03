#include <iostream>
#include <unordered_map>
#include <boost/range/combine.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <fstream>


using namespace boost::property_tree;
using namespace boost;

class Convert
{
	void csvxmlHelper(std::string path)
	{
		static int ctr;
		static std::unordered_map<std::string, int> fileNames;
		std::vector<std::string> tags;
		std::vector<std::string> rows;
		std::ifstream file(path);
		std::string line;

		std::getline(file, line);

		auto tokenize = [](std::string line)
		{
			std::vector<std::string> col_names;

			tokenizer<escaped_list_separator<char> > tk(line, escaped_list_separator<char>());
			for (tokenizer<escaped_list_separator<char> >::iterator i(tk.begin()); i != tk.end(); ++i)
				col_names.push_back(*i);

			return col_names;
		};

		auto create_XML = [](std::vector<std::string>& tags, std::vector<std::string> rows)
		{
			ptree XMLobjectL;
			std::string tag, value;

			for (auto i : boost::combine(tags, rows))
			{
				//tag contains tags, value contains corresponding values
				boost::tie(tag, value) = i;
				XMLobjectL.put("annotation.object." + tag, value);
			}
			write_xml("C:\\Users\\gmano\\Desktop\\csv_xml\\" + std::to_string(ctr) + ".xml", XMLobjectL, std::locale(),
				xml_writer_make_settings<ptree::key_type>(' ', 1u));
			ctr++;
		};

		tags = tokenize(line);

		while (std::getline(file, line))
			create_XML(tags, tokenize(line));
	}

public:
	void csvTOxml(std::string path)
	{
		csvxmlHelper(path);
	}
};


int main() {
	Convert foo;
	foo.csvTOxml("C:\\Users\\gmano\\Desktop\\csv_xml\\csv.csv");
}
